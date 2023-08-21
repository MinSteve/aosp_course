#define LOG_TAG "invcase_aidl_hal_test"

#include <aidl/Gtest.h>
#include <aidl/Vintf.h>

#include <aidl/android/hardware/invcase/IInvcase.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::android::hardware::invcase::IInvcase;

class InvcaseAidl : public testing::TestWithParam<std::string> {
public:
    virtual void SetUp() override {
        const auto instance = GetParam();
        ASSERT_TRUE(AServiceManager_isDeclared(instance.c_str()));
        auto invBinder = ndk::SpAIBinder(AServiceManager_waitForService(instance.c_str()));
        inv_ = IInvcase::fromBinder(invBinder);
        ASSERT_NE(inv_, nullptr);
    }

    std::shared_ptr<IInvcase> inv_;
};

/*
 * Ensure inverses the character's case work
 */
TEST_P(InvcaseAidl, TestInverseChars) {
    std::string testString = "AbcD";
    std::string getString = "";
    
    ASSERT_TRUE(inv_->putChars(testString).isOk());
    ASSERT_TRUE(inv_->getChars(&getString).isOk());
    ASSERT_EQ(getString, "aBCd");
}

GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(InvcaseAidl);
INSTANTIATE_TEST_SUITE_P(Invc, InvcaseAidl,
                         testing::ValuesIn(android::getAidlHalInstanceNames(IInvcase::descriptor)),
                         android::PrintInstanceNameToString);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ABinderProcess_setThreadPoolMaxThreadCount(1);
    ABinderProcess_startThreadPool();
    return RUN_ALL_TESTS();
}
