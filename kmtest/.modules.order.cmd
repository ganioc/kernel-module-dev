cmd_/mnt/android/project/kernel/kmtest/modules.order := {   echo /mnt/android/project/kernel/kmtest/kmtest.ko; :; } | awk '!x[$$0]++' - > /mnt/android/project/kernel/kmtest/modules.order
