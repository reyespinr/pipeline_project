FROM mcr.microsoft.com/devcontainers/base:ubuntu-20.04

# Install the required tools and libraries
RUN apt update \
    && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    clang-format \
    clang-tidy \
    cmake \
    g++ \
    gcc \
    gdb \
    libgtest-dev \
    make \
    python3 \
    python3-pip \
    python3-tk \ # This is for tkinter
    && pip3 install --no-cache-dir \
    && rm -rf /var/lib/apt/lists/*
