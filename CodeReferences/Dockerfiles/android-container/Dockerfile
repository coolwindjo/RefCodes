FROM ubuntu

LABEL maintainer "coolwind@hotmail.co.kr"

WORKDIR /

SHELL ["/bin/bash", "-c"]

ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt install -y cpu-checker openjdk-8-jdk vim git wget unzip libglu1 libpulse-dev libasound2 libc6  libstdc++6 libx11-6 libx11-xcb1 libxcb1 libxcomposite1 libxcursor1 libxi6  libxtst6 libnss3

# gradle
# gradle local installation
# ARG GRADLE_VERSION=5.4.1
# ARG ANDROID_API_LEVEL=28
# ARG ANDROID_BUILD_TOOLS_LEVEL=28.0.3
ARG GRADLE_VERSION=6.5.1
ARG ANDROID_API_LEVEL=30
ARG ANDROID_BUILD_TOOLS_LEVEL=30.0.4
# ARG EMULATOR_NAME='test'
# RUN wget https://services.gradle.org/distributions/gradle-${GRADLE_VERSION}-bin.zip -P /tmp \
# && unzip -d /opt/gradle /tmp/gradle-${GRADLE_VERSION}-bin.zip \
# && mkdir /opt/gradlew \
# && /opt/gradle/gradle-${GRADLE_VERSION}/bin/gradle wrapper --gradle-version ${GRADLE_VERSION} --distribution-type all -p /opt/gradlew  \
# && /opt/gradle/gradle-${GRADLE_VERSION}/bin/gradle wrapper -p /opt/gradlew
# gradle wrapper
ENV GRADLE_USER_HOME=/cache
VOLUME $GRADLE_USER_HOME

# android 
# RUN wget 'https://dl.google.com/android/repository/sdk-tools-linux-4333796.zip' -P /tmp \
# && unzip -d /opt/android /tmp/sdk-tools-linux-4333796.zip \
ARG ANDROID_EMULATOR_PACKAGE_ARM="system-images;android-25;google_apis;armeabi-v7a"
ARG ANDROID_EMULATOR_PACKAGE_x86="system-images;android-${ANDROID_API_LEVEL};google_apis;x86"
ARG ANDROID_PLATFORM_VERSION="platforms;android-${ANDROID_API_LEVEL}"
ARG ANDROID_SDK_VERSION="sdk-tools-linux-4333796.zip"
ARG ANDROID_SDK_PACKAGES="${ANDROID_EMULATOR_PACKAGE_ARM} ${ANDROID_EMULATOR_PACKAGE_x86} ${ANDROID_PLATFORM_VERSION} platform-tools emulator"

RUN wget https://dl.google.com/android/repository/${ANDROID_SDK_VERSION} -P /tmp && \
    unzip -d /opt/android /tmp/${ANDROID_SDK_VERSION}
ENV ANDROID_HOME=/opt/android
ENV PATH "$PATH:$ANDROID_HOME/emulator:$ANDROID_HOME/tools/bin:$ANDROID_HOME/platform-tools"

# sdkmanager
# && yes Y | /opt/android/tools/bin/sdkmanager --install "platform-tools" "system-images;android-${ANDROID_API_LEVEL};google_apis;x86" "platforms;android-${ANDROID_API_LEVEL}" "build-tools;${ANDROID_BUILD_TOOLS_LEVEL}" "emulator" \
# && yes Y | /opt/android/tools/bin/sdkmanager --licenses \
RUN mkdir /root/.android/
RUN touch /root/.android/repositories.cfg
# RUN sdkmanager --list --verbose
RUN yes Y | sdkmanager --licenses 
RUN yes Y | sdkmanager --verbose --no_https ${ANDROID_SDK_PACKAGES} 

# avdmanager
# && echo "no" | /opt/android/tools/bin/avdmanager --verbose create avd --force --name "test" --device "pixel" --package "system-images;android-${ANDROID_API_LEVEL};google_apis;x86" --tag "google_apis" --abi "x86"
ENV EMULATOR_NAME_x86="android_x86"
ENV EMULATOR_NAME_ARM="android_arm"
RUN echo "no" | avdmanager --verbose create avd --force --name "${EMULATOR_NAME_x86}" --device "pixel" --package "${ANDROID_EMULATOR_PACKAGE_x86}"
RUN echo "no" | avdmanager --verbose create avd --force --name "${EMULATOR_NAME_ARM}" --device "pixel" --package "${ANDROID_EMULATOR_PACKAGE_ARM}"

# ENV GRADLE_HOME=/opt/gradle/gradle-$GRADLE_VERSION \
# ANDROID_HOME=/opt/android
# ENV PATH "$PATH:$GRADLE_HOME/bin:/opt/gradlew:$ANDROID_HOME/emulator:$ANDROID_HOME/tools/bin:$ANDROID_HOME/platform-tools"
ENV LD_LIBRARY_PATH "$ANDROID_HOME/emulator/lib64:$ANDROID_HOME/emulator/lib64/qt/lib"

# clean up
RUN  apt-get remove -y unzip wget && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*   

ADD start.sh /
RUN chmod +x start.sh
