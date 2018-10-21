# cwalker

[![CircleCI](https://circleci.com/gh/mathetake/cwalker.svg?style=shield)](https://circleci.com/gh/mathetake/cwalker)
[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)


_cwalker_ is an implementation of Walker's sampling method in c++.

Ref:  http://www.keithschwarz.com/darts-dice-coins

# build & test

1. setup cmake
```bash
git clone https://github.com/mathetake/cwalker
cd cwalker
mkdir build && cd build
cmake ..
```

2. build && run
```
make
./walker
```

3. run test
```$xslt
make test
```

# LICENSE

MIT
