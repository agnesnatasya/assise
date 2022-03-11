sudo ndctl create-namespace -m fsdax -e namespace0.0 -f
sudo chmod 777 /dev/pmem0
mkfs -t ext4 /dev/pmem0
# mount -o dax /dev/pmem0 /mnt/pmem/
# I dont think we need to mount it because 