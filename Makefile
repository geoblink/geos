.PHONY: fmt check

SRCS = coord.go coordseq.go cwrappers.go geom.go geos.c geos.go geos.h helper.go prepared.go types.go wkb.go wkt.go

all: build

## TODO fix. There are problems with _attribute_
.PHONY: cwrappers.go
cwrappers.go: geoscapi.py
	poetry run python3 $< /usr/local/include/geos_c.h > $@
	gofmt -w $@

build: $(SRCS)
	go build

check:
	go test ./... -v

fmt:
	go fmt ./...

install:
	go install ./...

set-up-compile:
	git clone https://github.com/OSGeo/geos /tmp/lib-geos
	sudo apt-get -y update && sudo apt-get install -y autoconf libtool automake
	cd /tmp/lib-geos &&  \
		./autogen.sh &&  \
		./configure && \
	 	make && \
		make check && \
		sudo make install \
		sudo ldconfig
