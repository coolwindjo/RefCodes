docker build \
--build-arg GRADLE_VERSION=6.5.1 \
--build-arg ANDROID_API_LEVEL=30 \
--build-arg ANDROID_BUILD_TOOLS_LEVEL=30.0.4 \
--build-arg EMULATOR_NAME=test \
-t android-container:sunflower . 
