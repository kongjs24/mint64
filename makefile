all: BootLoader Disk.img

BootLoader:
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	make -C 00.BootLoader
	
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo

Disk.img: 00.BootLoader/BootLoader.bin
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	cp 00.BootLoader/BootLoader.bin Disk.img
	
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo

clean:
	make -C 00.BootLoader clean
	rm -f Disk.img