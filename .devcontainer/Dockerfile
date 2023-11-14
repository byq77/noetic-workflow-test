FROM osrf/ros:noetic-desktop-full

ARG USERNAME=ros
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ARG ROS_DISTRO=noetic
ARG WORKSPACE

SHELL ["/bin/bash", "-c"]

# Create a non-root user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # Add sudo support for the non-root user
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/*

USER ${USERNAME}

ENV DEBIAN_FRONTEND=noninteractive
# Install dependencies
RUN sudo apt-get update \
    && sudo apt-get install -y --no-install-recommends \
    software-properties-common \
    apt-transport-https \
    python3-pip \
    python3-catkin-tools \
    python3-setuptools \
    bash-completion \
    clang \
    clang-format \
    cppcheck \
    curl \
    ssh \
    git \
    vim \
    gdb \
    tree \
    wget \
    ncat \
    rsync \
    && sudo rm -rf /var/lib/apt/lists/*

RUN sudo mkdir -p /etc/apt/keyrings \
    && curl -sSf https://librealsense.intel.com/Debian/librealsense.pgp | sudo tee /etc/apt/keyrings/librealsense.pgp > /dev/null

RUN echo "deb [signed-by=/etc/apt/keyrings/librealsense.pgp] https://librealsense.intel.com/Debian/apt-repo `lsb_release -cs` main" | \
    sudo tee /etc/apt/sources.list.d/librealsense.list

RUN sudo apt-get update && \
    sudo apt-get install -y --no-install-recommends \
    librealsense2-dkms \
    librealsense2-utils \
    ros-${ROS_DISTRO}-realsense2-camera \
    ros-${ROS_DISTRO}-rviz-imu-plugin \
    ros-${ROS_DISTRO}-swri-console \
    ros-${ROS_DISTRO}-plotjuggler \
    && sudo rm -rf /var/lib/apt/lists/*

################
# Expose the nvidia driver to allow opengl 
# Dependencies for glvnd and X11.
################
RUN sudo apt-get update \
    && sudo apt-get install -y -qq --no-install-recommends \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6 \
    && sudo rm -rf /var/lib/apt/lists/*

# Set up autocompletion for user
RUN echo "if [ -f /opt/ros/${ROS_DISTRO}/setup.bash ]; then source /opt/ros/${ROS_DISTRO}/setup.bash; fi" >> /home/${USERNAME}/.bashrc
RUN echo "if [ -f ${WORKSPACE}/devel/setup.bash ]; then source ${WORKSPACE}/devel/setup.bash; fi" >> /home/${USERNAME}/.bashrc

RUN python3 -m pip install black pyserial

ENV DEBIAN_FRONTEND=dialog

WORKDIR ${WORKSPACE}
