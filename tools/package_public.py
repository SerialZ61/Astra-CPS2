"""Package one language of Astra CPS2 with its tagged source and notices."""

import argparse
import hashlib
import io
from pathlib import Path, PurePosixPath
import subprocess
import tarfile
from zipfile import ZIP_DEFLATED, ZipFile, ZipInfo


ROOT = Path(__file__).resolve().parents[1]
APP = "3ds/AstraCPS2/"
REFERENCE_FR = "11faa88879cd89bbf3b62e3af9ffe698647cd9ab3d5be9c4e9997cb907bf880e"
SOURCE_EXTENSIONS = {".c", ".cpp", ".h", ".inc", ".s", ".pica", ".mk", ".md",
                     ".py", ".ps1", ".txt", ".csv", ".json"}
SPECIAL = {"Makefile", ".gitignore", ".gitattributes", "assets/icon.png"}


def source_files(ref):
    archive = subprocess.check_output(["git", "archive", "--format=tar", ref], cwd=ROOT)
    files = {}
    with tarfile.open(fileobj=io.BytesIO(archive)) as tree:
        for entry in tree.getmembers():
            if entry.isdir():
                continue
            path = PurePosixPath(entry.name)
            if (not entry.isfile() or path.is_absolute() or ".." in path.parts
                    or (entry.name not in SPECIAL and path.suffix.lower() not in SOURCE_EXTENSIONS)):
                raise ValueError(f"Unexpected source file: {entry.name}")
            files[entry.name] = tree.extractfile(entry).read()
    return files


def package(tag, language, binary, output):
    files = source_files(tag)
    program = binary.read_bytes()
    if program[:4] != b"3DSX":
        raise ValueError("Expected a 3DSX executable")
    if tag == "v0.6" and language == "fr" and hashlib.sha256(program).hexdigest() != REFERENCE_FR:
        raise ValueError("The French v0.6 must match the hardware reference")
    files[APP + "AstraCPS2.3dsx"] = program
    for name, data in list(files.items()):
        if name.startswith("notices/"):
            files[APP + name] = data
    files["SHA256SUMS.txt"] = "".join(
        f"{hashlib.sha256(files[name]).hexdigest()}  {name}\n" for name in sorted(files)
    ).encode("utf-8")
    output.parent.mkdir(parents=True, exist_ok=True)
    pending = output.with_suffix(".tmp")
    with ZipFile(pending, "w") as archive:
        for name, data in sorted(files.items()):
            archive.writestr(ZipInfo(name), data, ZIP_DEFLATED, compresslevel=9)
        archive.writestr(ZipInfo(APP + "roms/"), b"")
    with ZipFile(pending) as archive:
        if archive.testzip() or any(archive.read(name) != data for name, data in files.items()):
            raise OSError("Release package verification failed")
    pending.replace(output)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("tag")
    parser.add_argument("language", choices=["en", "fr"])
    parser.add_argument("binary", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    package(args.tag, args.language, args.binary, args.output)
