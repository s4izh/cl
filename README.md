# cl setup

build docker image with antrl

```sh
docker build -t ubuntu_antlr .
```

run docker image with:

```sh
docker run -it --rm -v "$PWD:/antlr-dev" ubuntu_antlr
```
