FROM ubuntu:20.04

RUN apt-get update & apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    uuid-dev \ 
    openjdk-11-jre-headless \
    libantlr4-runtime-dev

RUN wget https://www.antlr.org/download/antlr-4.9.2-complete.jar && \
    mv antlr-4.9.2-complete.jar /usr/local/lib/antlr-4.9.2-complete.jar && \
    echo "alias antlr4='java -jar /usr/local/lib/antlr-4.9.2-complete.jar'" >> ~/.bashrc

RUN wget https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-linux-x86_64-2.5.0.tar.gz && \
    tar -C /usr/local -xzf libtensorflow-cpu-linux-x86_64-2.5.0.tar.gz && \
    ldconfig

WORKDIR /app

COPY . /app

RUN mkdir build && cd build && \
    cmake .. && \
    make

CMD ["./build/TensorJ"]