/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <aidl/android/hardware/dumpstate/BnDumpstateDevice.h>
#include <aidl/android/hardware/dumpstate/IDumpstateDevice.h>
#include <android/binder_status.h>

#include <string>

namespace aidl {
namespace android {
namespace hardware {
namespace dumpstate {

class Dumpstate : public BnDumpstateDevice {
  public:
    Dumpstate();

    ::ndk::ScopedAStatus dumpstateBoard(const std::vector<::ndk::ScopedFileDescriptor>& in_fds,
                                        IDumpstateDevice::DumpstateMode in_mode,
                                        int64_t in_timeoutMillis) override;

    ::ndk::ScopedAStatus getVerboseLoggingEnabled(bool* _aidl_return) override;
    ::ndk::ScopedAStatus setVerboseLoggingEnabled(bool in_enable) override;
    binder_status_t dump(int fd, const char** args, uint32_t numArgs) override;

  private:
    const std::string kAllSections = "all";

    std::vector<std::pair<std::string, std::function<void(int)>>> mTextSections;

    void dumpTextSection(int fd, std::string const& sectionName);

    // Text sections that can be dumped individually on the command line in
    // addition to being included in full dumps
    void dumpPowerSection(int fd);
    void dumpThermalSection(int fd);
    void dumpPreTouchSection(int fd);
    void dumpTouchSection(int fd);
    void dumpCpuSection(int fd);
    void dumpDevfreqSection(int fd);
    void dumpMemorySection(int fd);
    void dumpDisplaySection(int fd);
    void dumpSensorsUSFSection(int fd);
    void dumpMiscSection(int fd);
    void dumpCameraSection(int fd);
};

}  // namespace dumpstate
}  // namespace hardware
}  // namespace android
}  // namespace aidl
