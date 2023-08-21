# Input Framework

1. Rpi4 - Device tree
- Add below node to kernel-raspi4/common/arch/arm/boot/dts/bcm2711-rpi-4-b.dts
        demo_input {
                compatible = "raspi4,demo_input";
                inputkey-gpios = <&gpio 22 GPIO_ACTIVE_LOW>, //BACK key
                                 <&gpio 27 GPIO_ACTIVE_LOW>, //ENTER key
                                 <&gpio 19 GPIO_ACTIVE_LOW>, //UP key
                                 <&gpio 16 GPIO_ACTIVE_LOW>, //DOWN key
                                 <&gpio 26 GPIO_ACTIVE_LOW>, //LEFT key
                                 <&gpio 20 GPIO_ACTIVE_LOW>; //RIGHT Key
                status = "okay";
        };

2. demo_input driver
- Put demo_input folder to kernel-raspi4/common/drivers/ folder
- modify kernel-raspi4/common/drivers/Makefile by adding below line to the bottom
	obj-y                           += demo_input/