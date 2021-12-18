# FIPS disable

# "fastboot oem sha1sum fips" gives a sha1sum of 7d76d48d64d7ac5411d714a4bb83f37e3e5b8df6
# Thus we create a file, fips.img using "dd if=/dev/zero of=fips.img bs=2097152 count=1"
# "sha1sum fips.img" will produce the same hash
# A zeroed out partition means that FIPS is disabled.

LOCAL_PATH := $(call my-dir)

$(call add-radio-file,radio/fips.img)
