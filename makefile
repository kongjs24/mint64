all: BootLoader Kernel32 Disk.img

BootLoader:
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	make -C 00.BootLoader
	
	@echo
	@echo  ================ Success Build Boot Loader ===================
	@echo

Kernel32:
	@echo
	@echo ====================== Build 32bit kernel ======================
	@echo
	
	make -C 01.Kernel32
	
	@echo
	@echo ================ Success Build 32bit kernel ======================
	@echo

Disk.img: 00.BootLoader/BootLoader.bin 01.Kernel32/Kernel32.bin
	@echo
	@echo  ====================== make Disk image ======================
	@echo

	cat $^ > Disk.img

	@echo
	@echo  ================ Success make Disk image ======================
	@echo

clean:
	make -C 00.BootLoader clean
	make -C 01.Kernel32 clean
	rm -f Disk.img