# citro3d and picasso are part of devkitPro's 3ds-dev package group.
# Use an in-tree SDK build when the host has only the basic devkitARM tools.
CITRO3D_DIR ?= $(if $(wildcard $(SDK)/lib/libcitro3d.a),$(SDK),vendor/citro3d)
PICASSO ?= $(if $(wildcard vendor/picasso/picasso.exe),vendor/picasso/picasso.exe,picasso)
DISPLAY_CFLAGS := -I$(CITRO3D_DIR)/include
DISPLAY_LIBS := -L$(CITRO3D_DIR)/lib -lcitro3d
DISPLAY_OBJECTS := $(OBJ)/app/quad_shader.o

$(OBJ)/app/quad.shbin: app/quad.v.pica
	@mkdir -p $(@D)
	$(PICASSO) -o $@ $<

$(OBJ)/app/quad_shader.o: app/quad_shader.S $(OBJ)/app/quad.shbin
	$(CC) $(ARCH) -DASTRA_QUAD_SHADER='"$(OBJ)/app/quad.shbin"' -c $< -o $@
