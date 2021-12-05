LOCAL_PATH := $(call my-dir)

ifeq ($(LOCAL_TARGET_PRODUCT), $(ORIOLE_PRODUCT))
        RADIO_FILES := $(wildcard $(LOCAL_PATH)/$(LOCAL_TARGET_PRODUCT)/*.img)
else ifeq ($(LOCAL_TARGET_PRODUCT), $(RAVEN_PRODUCT)))
        RADIO_FILES := $(wildcard $(LOCAL_PATH)/$(LOCAL_TARGET_PRODUCT)/*.img)
endif
$(foreach f, $(notdir $(RADIO_FILES)),$(call add-radio-file,$(f)))
