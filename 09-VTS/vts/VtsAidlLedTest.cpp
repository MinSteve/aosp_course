/*
 * Copyright (C) 2023 Dung Tran Anh
 */

#define LOG_TAG "led_aidl_hal_test"

#include <aidl/Gtest.h>
#include <aidl/Vintf.h>

#include <aidl/vendor/cocktail/hardware/led/ILed.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::cocktail::hardware::led::ILed;

class LedAidl : public testing::TestWithParam<std::string> {
public:
    virtual void SetUp() override {
        const auto instance = GetParam();
        ASSERT_TRUE(AServiceManager_isDeclared(instance.c_str()));
        auto ledBinder = ndk::SpAIBinder(AServiceManager_waitForService(instance.c_str()));
        led_ = ILed::fromBinder(ledBinder);
        ASSERT_NE(led_, nullptr);
    }

    std::shared_ptr<ILed> led_;
};

/*
 * Ensure setLed and getled work
 */
TEST_P(LedAidl, TestLed) {
    std::int32_t setValue = 1;
    std::int32_t getValue = 0;
    
    ASSERT_TRUE(led_->setLed(setValue).isOk());
    ASSERT_TRUE(led_->getLed(&getValue).isOk());
    ASSERT_EQ(getValue, 1);
}

GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(LedAidl);
INSTANTIATE_TEST_SUITE_P(Ledhal, LedAidl,
                         testing::ValuesIn(android::getAidlHalInstanceNames(ILed::descriptor)),
                         android::PrintInstanceNameToString);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ABinderProcess_setThreadPoolMaxThreadCount(1);
    ABinderProcess_startThreadPool();
    return RUN_ALL_TESTS();
}