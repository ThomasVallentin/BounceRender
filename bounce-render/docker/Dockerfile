FROM aswf/ci-vfxall:2021

# Download & install embree
RUN wget https://github.com/embree/embree/releases/download/v3.13.3/embree-3.13.3.x86_64.linux.tar.gz -O /usr/tmp/embree-3.13.3.tar.gz
RUN tar -xf /usr/tmp/embree-3.13.3.tar.gz -C /opt
RUN source /opt/embree-3.13.3.x86_64.linux/embree-vars.sh

# Install glfw3 dependencies
RUN sudo yum install libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel

# Cloning Dear ImGui
RUN git clone https://github.com/ocornut/imgui.git -b docking

# Cleanup
RUN rm -rf /usr/tmp/*
