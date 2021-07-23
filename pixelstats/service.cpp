/*
 * Copyright (C) 2018 The Android Open Source Project
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

#define LOG_TAG "pixelstats"

#include <android-base/logging.h>
#include <pixelstats/SysfsCollector.h>
#include <pixelstats/UeventListener.h>

#include <thread>

using android::hardware::google::pixel::SysfsCollector;
using android::hardware::google::pixel::UeventListener;

#define UFSHC_PATH(filename) "/dev/sys/block/bootdevice/" #filename
const struct SysfsCollector::SysfsPaths sysfs_paths = {
        .SlowioReadCntPath = UFSHC_PATH(slowio_read_cnt),
        .SlowioWriteCntPath = UFSHC_PATH(slowio_write_cnt),
        .SlowioUnmapCntPath = UFSHC_PATH(slowio_unmap_cnt),
        .SlowioSyncCntPath = UFSHC_PATH(slowio_sync_cnt),
        .CycleCountBinsPath = "/sys/class/power_supply/battery/cycle_counts",
        .UFSLifetimeA = UFSHC_PATH(health_descriptor/life_time_estimation_a),
        .UFSLifetimeB = UFSHC_PATH(health_descriptor/life_time_estimation_b),
        .UFSLifetimeC = UFSHC_PATH(health_descriptor/life_time_estimation_c),
        .UFSHostResetPath = UFSHC_PATH(err_stats/dev_reset_count),
        .F2fsStatsPath = "/sys/fs/f2fs/",
        .ImpedancePath = "/sys/devices/platform/audiometrics/speaker_impedance",
        .CodecPath = "/sys/devices/platform/audiometrics/codec_state",
        .EEPROMPath = "/dev/battery_history",
        .MitigationPath = "/sys/devices/virtual/pmic/mitigation"};
const struct UeventListener::UeventPaths ueventPaths = {
        .AudioUevent = "/devices/virtual/amcs/amcs",
        .WirelessChargerPtmcPath = "/sys/class/power_supply/wireless/device/ptmc_id"};

int main() {
    LOG(INFO) << "starting PixelStats";

    UeventListener ueventListener(ueventPaths);
    std::thread listenThread(&UeventListener::ListenForever, &ueventListener);
    listenThread.detach();

    SysfsCollector collector(sysfs_paths);
    collector.collect();  // This blocks forever.

    return 0;
}
