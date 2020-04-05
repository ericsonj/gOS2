TARGET          = Release/gOS2.bin
TARGET_ZIP      = Release/gOS2.bin.zip

TARGETS = $(TARGET_ZIP)


$(TARGET): $(OBJECTS)
	$(call logger-compile,"OUT",$@)
	$(LD) -o $@ $(OBJECTS) $(LDFLAGS)

$(TARGET_ZIP): $(TARGET)
	$(call logger-compile,"ZIP",$@)
	zip Release/gOS2.bin.zip $(TARGET)


clean_targets:
	rm -rf $(TARGET) $(TARGET_ZIP)
