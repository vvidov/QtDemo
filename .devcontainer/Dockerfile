FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gdb \
    python3 \
    python3-pip \
    qt6-base-dev \
    qt6-base-private-dev \
    qtcreator \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m -s /bin/bash vscode
USER vscode

# Set up Qt debug helpers
RUN mkdir -p /home/vscode/.gdb/qt6
COPY --chown=vscode:vscode .gdbinit /home/vscode/.gdbinit

# Get Qt6 GDB helpers
RUN git clone --depth 1 https://code.qt.io/qt/qtbase.git /tmp/qtbase && \
    cp -r /tmp/qtbase/util/gdb/* /home/vscode/.gdb/qt6/ && \
    rm -rf /tmp/qtbase

# Set up Python path for Qt debug helpers
ENV PYTHONPATH=/home/vscode/.gdb/qt6

WORKDIR /workspace
