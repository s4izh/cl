FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    unzip \
    wget \
    default-jre \
    antlr4 \
    make \
    g++ \
    gcc \
    libantlr4-runtime-dev

WORKDIR /antlr-dev

CMD ["/bin/bash"]

