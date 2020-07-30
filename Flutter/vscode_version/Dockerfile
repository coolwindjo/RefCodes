# FROM ubuntu
FROM ubuntu:18.04
   
LABEL maintainer "coolwind@hotmail.co.kr"
WORKDIR /
SHELL ["/bin/bash", "-c"]

# Prerequisites
ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt update && apt install -y curl wget git unzip zip sudo xz-utils vim cpu-checker openjdk-8-jdk libglu1-mesa libpulse-dev libasound2 libc6  libstdc++6 libx11-6 libx11-xcb1 libxcb1 libxcomposite1 libxcursor1 libxi6  libxtst6 libnss3
    # RUN apt update && apt install -y cpu-checker openjdk-8-jdk vim git wget unzip libglu1 libpulse-dev libasound2 libc6  libstdc++6 libx11-6 libx11-xcb1 libxcb1 libxcomposite1 libxcursor1 libxi6  libxtst6 libnss3
    # RUN apt update && apt install -y curl git unzip xz-utils zip libglu1-mesa openjdk-8-jdk wget

# gradle wrapper
ENV GRADLE_USER_HOME=/cache
VOLUME $GRADLE_USER_HOME

# gradle local installation
ARG GRADLE_VERSION=6.5.1
# RUN wget https://services.gradle.org/distributions/gradle-${GRADLE_VERSION}-bin.zip -P /tmp \
# && unzip -d /opt/gradle /tmp/gradle-${GRADLE_VERSION}-bin.zip \
# && mkdir /opt/gradlew \
# && /opt/gradle/gradle-${GRADLE_VERSION}/bin/gradle wrapper --gradle-version ${GRADLE_VERSION} --distribution-type all -p /opt/gradlew  \
# && /opt/gradle/gradle-${GRADLE_VERSION}/bin/gradle wrapper -p /opt/gradlew

# Set up Android SDK
ARG ANDROID_SDK_VERSION="sdk-tools-linux-4333796.zip"
ENV ANDROID_SDK_URL="https://dl.google.com/android/repository/${ANDROID_SDK_VERSION}"
RUN wget ${ANDROID_SDK_URL} -P /tmp && \
    unzip -d /opt/android /tmp/${ANDROID_SDK_VERSION}
    # RUN wget -O sdk-tools.zip https://dl.google.com/android/repository/sdk-tools-linux-4333796.zip
    # RUN unzip sdk-tools.zip && rm sdk-tools.zip
    # RUN mkdir -p Android/sdk
    # ENV ANDROID_SDK_ROOT /home/developer/Android/sdk
    # RUN mv tools Android/sdk/tools

# sdkmanager
# RUN /opt/android/tools/bin/sdkmanager --list --verbose
RUN yes Y | /opt/android/tools/bin/sdkmanager --licenses 
    # RUN cd Android/sdk/tools/bin && yes | ./sdkmanager --licenses

# Prepare Android directories and system variables
# RUN mkdir -p .android && touch .android/repositories.cfg
RUN mkdir -p /root/.android/
RUN touch /root/.android/repositories.cfg

ARG ANDROID_API_LEVEL=29
# ARG ANDROID_BUILD_TOOLS_LEVEL=28.0.3
ARG ANDROID_BUILD_TOOLS_LEVEL=29.0.3
ENV ANDROID_EMULATOR_PACKAGE_ARM="system-images;android-25;google_apis;armeabi-v7a"
ENV ANDROID_EMULATOR_PACKAGE_x86="system-images;android-${ANDROID_API_LEVEL};google_apis;x86"
ENV ANDROID_PLATFORM_VERSION="platforms;android-${ANDROID_API_LEVEL}"
ENV ANDROID_SOURCE_VERSION="sources;android-${ANDROID_API_LEVEL}"
ENV ANDROID_BUILD_TOOLS="build-tools;${ANDROID_BUILD_TOOLS_LEVEL}"
ENV ANDROID_SDK_PACKAGES="${ANDROID_EMULATOR_PACKAGE_ARM} ${ANDROID_EMULATOR_PACKAGE_x86} ${ANDROID_PLATFORM_VERSION} ${ANDROID_BUILD_TOOLS} ${ANDROID_SOURCE_VERSION} platform-tools emulator"
RUN yes Y | /opt/android/tools/bin/sdkmanager --verbose --no_https ${ANDROID_SDK_PACKAGES} 
# RUN cd Android/sdk/tools/bin && ./sdkmanager "patcher;v4"
# && yes Y | /opt/android/tools/bin/sdkmanager --install  \
ENV ANDROID_HOME=/opt/android
ENV PATH "$PATH:$ANDROID_HOME/emulator:$ANDROID_HOME/tools/bin:$ANDROID_HOME/platforms:$ANDROID_HOME/platform-tools"
    # ENV PATH "$PATH:/home/developer/Android/sdk/platform-tools"
    # ENV PATH="$ANDROID_SDK_ROOT/emulator:$ANDROID_SDK_ROOT/platform-tools:$ANDROID_SDK_ROOT/platforms:$PATH"

ARG ANDROID_TOOLS_VERSION="commandlinetools-linux-6200805_latest.zip"
ENV ANDROID_TOOLS_URL="https://dl.google.com/android/repository/${ANDROID_TOOLS_VERSION}"
ENV PATH="$ANDROID_HOME/cmdline-tools/tools/bin:$PATH"

# Set up new user
# RUN useradd -ms /bin/bash coolwind
# RUN echo -e "cool\ncool" | passwd coolwind
# RUN adduser --disabled-password --gecos "" coolwind
# USER coolwind
# WORKDIR /home/coolwind

# Download Flutter SDK
ENV FLUTTER_CHANNEL="master"
# ENV FLUTTER_VERSION="1.17.5"
# ENV FLUTTER_URL="https://storage.googleapis.com/flutter_infra/releases/$FLUTTER_CHANNEL/linux/flutter_linux_$FLUTTER_VERSION-$FLUTTER_CHANNEL.tar.xz"
# ENV FLUTTER_WEB_PORT="8090"
# ENV FLUTTER_DEBUG_PORT="42000"
# ENV FLUTTER_EMULATOR_NAME="emulator-5554"
ENV FLUTTER_HOME=${HOME}/flutter
ENV FLUTTER_ROOT=$FLUTTER_HOME
ENV PATH ${PATH}:${FLUTTER_HOME}/bin:${FLUTTER_HOME}/bin/cache/dart-sdk/bin
RUN git clone --branch ${FLUTTER_CHANNEL} https://github.com/flutter/flutter.git ${FLUTTER_HOME}

# avdmanager
# && echo "no" | /opt/android/tools/bin/avdmanager --verbose create avd --force --name "test" --device "pixel" --package "system-images;android-${ANDROID_API_LEVEL};google_apis;x86" --tag "google_apis" --abi "x86"

ENV EMULATOR_NAME_x86="android_x86"
ENV EMULATOR_NAME_ARM="android_arm"
RUN echo "no" | avdmanager --verbose create avd --force --name "${EMULATOR_NAME_x86}" --device "pixel" --package "${ANDROID_EMULATOR_PACKAGE_x86}"
RUN echo "no" | avdmanager --verbose create avd --force --name "${EMULATOR_NAME_ARM}" --device "pixel" --package "${ANDROID_EMULATOR_PACKAGE_ARM}"

# ENV GRADLE_HOME=/opt/gradle/gradle-$GRADLE_VERSION \
# ENV PATH "$PATH:$GRADLE_HOME/bin:/opt/gradlew"
ENV LD_LIBRARY_PATH "$ANDROID_HOME/emulator/lib64:$ANDROID_HOME/emulator/lib64/qt/lib"

# clean up
RUN  apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*   

# ADD start.sh /
# RUN chmod +x start.sh

# Run basic check to download Dark SDK
RUN yes | flutter doctor --android-licenses && flutter doctor
