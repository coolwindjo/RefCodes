FROM ubuntu:18.04

USER root

ENV USER_NAME "coolwind"

RUN \
    apt-get update \
    apt-get install -y -q --no-install-recommends \
        -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" \
        build-essential \
        chrpath \
        cpio \
        diffstat \
        file \
        g++-multilib \
        gawk \
        gcc-multilib \
        git-core \
        locales \
        openssh-client \
        python \
        python3 \
        socat \
        sudo \
        texinfo \
        tmux \
        unzip \
        wget \
        vim \
    && rm -rf /var/lib/apt/lists/* && \
    locale-gen en_US.UTF-8

    ENV LANG='en_US.UTF-8' LANGUAGE='en_US:en' LC_ALL='en_US.UTF-8'

RUN \
    apt-get update && \
    apt-get install -y -q --no-install-recommends \
        -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/* && \
    wget -O /usr/local/bin/repo https://storage.googleapis.com/git-repo-downloads/repo && \
    chmod a+x /usr/local/bin/repo

# Clean up APT when done and set shell and user options.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*          \
        && rm /bin/sh && ln -s /bin/bash /bin/sh                            \
        && groupadd -g 1000 ${USER_NAME}                                    \
        && useradd -u 1000 -g 1000 -ms /bin/bash ${USER_NAME}               \
        && usermod -a -G sudo ${USER_NAME}                                  \
        && usermod -a -G users ${USER_NAME}                                 \
        && usermod --password ${USER_NAME} ${USER_NAME}                     \
        && usermod --password toor root                                     \
        && passwd -d root                                                   \
        && passwd -d ${USER_NAME}


# Run as yocto user from the installation path
RUN install -o 1000 -g 1000 -m 2777  -d ${EXCH_PATH}                        \
        && install -o 1000 -g 1000 -m 2777 -d ${EXCH_PATH_INPUT}            \
        && install -o 1000 -g 1000 -m 2777 -d ${EXCH_PATH_OUTPUT}


USER ${USER_NAME}