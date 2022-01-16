cmd_/mnt/android/project/kernel/lkmexam/modules.order := {   echo /mnt/android/project/kernel/lkmexam/lkmexam.ko; :; } | awk '!x[$$0]++' - > /mnt/android/project/kernel/lkmexam/modules.order
