all: debug release

configure: 
	node-gyp configure

debug: configure
	node-gyp build --debug

release: configure
	node-gyp build

clean:
	find build -type f -maxdepth 1 -exec rm -fv {} \;
