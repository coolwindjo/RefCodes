#
# Docker Bionic image to build Yocto 3.0
#
FROM ubuntu:18.04

# RUN Statement to install dependencies
# Keep the dependency list as short as reasonable
RUN apt-get update && \
apt-get install -y bc bison bsdmainutils build-essential curl locales \
flex g++-multilib gcc-multilib git gnupg gperf lib32ncurses5-dev \
lib32z1-dev libncurses5-dev git-lfs \
libsdl1.2-dev libxml2-utils lzop \
openjdk-8-jdk lzop wget git-core unzip \
genisoimage sudo socat xterm gawk cpio texinfo \
gettext vim diffstat chrpath libsdl1.2-dev \
python-mako libusb-1.0-0-dev exuberant-ctags \
pngcrush schedtool xsltproc zip zlib1g-dev libswitch-perl && \
apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# ADD repo command to rootfs
ADD https://commondatastorage.googleapis.com/git-repo-downloads/repo /usr/local/bin/
RUN chmod 755 /usr/local/bin/*

# RUN command to setup users and permissions
# ===== create user/setup environment =====
# Replace 1000 with your user/group id
RUN export uid=1000 gid=1000 user=coolwind && \
mkdir -p /home/${user} && \
echo "${user}:x:${uid}:${gid}:${user},,,:/home/${user}:/bin/bash" >> /etc/passwd && \
echo "${user}:x:${uid}:" >> /etc/group && \
echo "${user} ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/${user} && \
chmod 0440 /etc/sudoers.d/${user} && \
chown ${uid}:${gid} -R /home/${user}

# Enable compiler cache to speed up builds 
# Improve rebuild performance by enabling compiler cache
ENV USE_CCACHE 1
ENV CCACHE_DIR /home/coolwind/.ccache

# Specify locale
# Set the locale
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8

# Setup User and its home directory
ENV HOME /home/coolwind
ENV USER coolwind
USER coolwind
