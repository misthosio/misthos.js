install-deps:
	yarn install

bsb:
	node_modules/.bin/bsb -clean-world
	node_modules/.bin/bsb -make-world -w

test:
	./node_modules/.bin/jest --clearCache
	NODE_ENV=test ./node_modules/.bin/jest --env=jsdom --watch
