
SUBDIRS:=`find ./ \( ! -regex '.*/\..*' \) -type d | cut -b 3- | tr '\n' ' ' | tr 'blank' ' '`

all:
	@for i in $(SUBDIRS); do \
		echo " Making $$i..."; \
		(cd ./$$i; $(MAKE) -s; ); \
		done

clean:
	@for i in $(SUBDIRS); do \
		echo " cleaning $$i..."; \
		(cd ./$$i; $(MAKE) -s clean; ); \
		done



