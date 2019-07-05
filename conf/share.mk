# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

define docker
  docker run --rm --volume $${REPO_HOME}:/mnt/scarv/libscarv --env DOCKER_GID="$(shell id --group)" --env DOCKER_UID="$(shell id --user)" --env REPO_HOME="/mnt/scarv/libscarv" --env HOST="native" --env ARCHS="$${ARCH}" --env KERNELS="$${KERNELS}" $${DOCKER_FLAGS} $${DOCKER_IMAGE} ${1}
endef
