FROM ubuntu:22.04

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    libgl1-mesa-dev \
    libgtest-dev \
    gdb \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Basic GDB configuration
RUN echo "set print pretty on" > /home/$USERNAME/.gdbinit && \
    echo "set print object on" >> /home/$USERNAME/.gdbinit && \
    echo "set print static-members on" >> /home/$USERNAME/.gdbinit && \
    echo "set print vtbl on" >> /home/$USERNAME/.gdbinit && \
    echo "set print demangle on" >> /home/$USERNAME/.gdbinit && \
    echo "set demangle-style gnu-v3" >> /home/$USERNAME/.gdbinit && \
    echo "set print array on" >> /home/$USERNAME/.gdbinit && \
    echo "set print array-indexes on" >> /home/$USERNAME/.gdbinit && \
    chown $USERNAME:$USERNAME /home/$USERNAME/.gdbinit

# Create and set permissions for workspace
RUN mkdir -p /workspaces \
    && chown -R $USERNAME:$USERNAME /workspaces \
    && chmod 755 /workspaces

USER $USERNAME
WORKDIR /workspaces

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog
