install-deps:
	yarn install

bsb:
	node_modules/.bin/bsb -clean-world
	node_modules/.bin/bsb -make-world -w

bsb-once:
	node_modules/.bin/bsb -make-world

test:
	./node_modules/.bin/jest --clearCache
	NODE_ENV=test ./node_modules/.bin/jest --env=jsdom --watch

ci:
	node_modules/.bin/jest --clearCache
	NODE_ENV=test CI=true ./node_modules/.bin/jest --env=jsdom --runInBand
