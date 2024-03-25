FROM ubuntu:22.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get -y install \
    build-essential \
    cmake \
    git \
    wget \ 
    bison \
    curl \
    flex 

RUN apt-get install -y apt-transport-https && \
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg && \
    mv bazel.gpg /etc/apt/trusted.gpg.d/ && \
    echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list && \
    apt-get update && \
    apt-get install -y bazel-6.5.0

WORKDIR /app

# Clone TensorFlow repository
RUN git clone --recurse-submodules https://github.com/tensorflow/tensorflow.git

COPY . /app

# Build TensorFlow C++ library
#RUN cd tensorflow && \
#    bazel build --config=opt //tensorflow:libtensorflow_cc.so


RUN mkdir build && cd build && \
    cmake .. && \
    make

CMD ["./build/TensorJ"]