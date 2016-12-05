all: BootLoader Disk.img

BootLoader:
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	make -C 00.BootLoader
	
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo

Kernel32:
	@echo
	@echo ====================== Build 32bit kernel ======================
	@echo
	
	make -C 01.Kernel32
	
	@echo
	@echo ====================== Build 32bit kernel ======================
	@echo

Disk.img: BootLoader Kernel32
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	cat 00.BootLoader/BootLoader.bin 01.Kernel32/VirtualOS.bin > Disk.img
	
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo

clean:
	make -C 00.BootLoader clean
	make -C 01.Kernel32 clean
	rm -f Disk.img