# Software Component : ...component_name...

## Introduction

...a description of the purpose and role of the component...


## Dependencies

- [connextauto-bus](https://github.com/rticommunity/connextauto-bus) provides the common data model, data interfaces, common build system, and component
launcher for components in the connextauto ecosystem, and it is:
  - Shared by all the components
  - Located at the path specified by the environment variable `$DATABUSHOME`

## Getting Started

- **(if not already done before)** Clone (or fork and clone) the [connextauto-bus](https://github.com/rticommunity/connextauto-bus) repo

      git clone git@github.com:rticommunity/connextauto-bus.git

- Clone (or fork and clone) this repo

      git clone <a_git_url_to_this_repository>

- **(if not done already)** Follow the [Getting Started](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#getting-started) instructions in the [`$DATABUSHOME/README.md`](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#getting-started) to generate the build system and to build the datatypes for the *RTI Connext SDK*(s) that will be used by this repo

- **(if not done already)** Follow the [Usage](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#usage) guidance in the [`$DATABUSHOME/README.md`](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#usage) for populating the `CMakeLists.txt` and how to `#include` header files for datatypes defined in the `$DATABUSHOME` repo for your applications.

- Generated build system for **this** repo, following the same instructions as above, in the [Getting Started](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#getting-started) section in the [`$DATABUSHOME/README.md`](https://github.com/rticommunity/connextauto-bus?tab=readme-ov-file#getting-started). 


- From **this** git repo's top-level directory, run the generated build script to build the applications
  - To build for *RTI Connext DDS Professional* SDK, e.g.:

            ./build/pro-$RTI_ARCH-Debug.sh

  - To build for *RTI Connext DDS Micro* SDK, e.g.:

            ./build/micro-$RTI_ARCH-Debug.sh

  - For more details, please refer to the documentation on the *common build system* located at [`$DATABUSHOME/doc/Build.md`](https://github.com/rticommunity/connextauto-bus/blob/develop/doc/Build.md).

- Run the applications using the launcher scripts

  - This repo uses the *common component launcher* provided by the [connextauto-bus](https://github.com/rticommunity/connextauto-bus) repo located at `$DATABUSHOME`. For documentation on the `$DATABUSHOME/bin/run` launcher utility, please refer to the documentation located at [`$DATABUSHOME/doc/Run.md`](https://github.com/rticommunity/connextauto-bus/blob/develop/doc/Run.md).


## Component Overview

...Provide an overview of the component, with links to additional docs ad needed...


---
(C) Copyright 2020-2025 Real-Time Innovations, Inc.  All rights reserved.

The use of this software is governed by the terms specified in the RTI Labs License Agreement, available at https://www.rti.com/terms/RTILabs. 

By accessing, downloading, or otherwise using this software, you agree to be bound by those terms.
