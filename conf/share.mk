# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

ifeq "${HOST}" "native"

endif

# =============================================================================

ifeq "${HOST}" "docker"

define docker
  echo $${DOCKER_REPO}
  echo $${DOCKER_TAG}
  echo $${DOCKER_FLAGS}
  git branch
  docker run --rm --volume $${REPO_HOME}:/mnt/scarv/libscarv --env DOCKER_GID="$(shell id --group)" --env DOCKER_UID="$(shell id --user)" --env REPO_HOME="/mnt/scarv/libscarv" --env HOST="native" --env ARCHS="$${ARCH}" --env KERNELS="$${KERNELS}" $${DOCKER_FLAGS} $${DOCKER_REPO}:$${DOCKER_TAG} ${1}
endef

endif

# =============================================================================
