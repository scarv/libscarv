# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

DOCKER_IMAGE = scarv/libscarv.${ARCH}
DOCKER_TAGS  = latest 0.1.0

${REPO_HOME}/build/${ARCH}/docker/Dockerfile       : ${REPO_HOME}/src/docker/Dockerfile ${REPO_HOME}/src/docker/${ARCH}/Dockerfile.in
	@m4 --include="${REPO_HOME}/src/docker/${ARCH}" ${<} > ${@}
${REPO_HOME}/build/${ARCH}/docker/entrypoint.sh    : ${REPO_HOME}/src/docker/entrypoint.sh
	@cp ${<} ${@}
${REPO_HOME}/build/${ARCH}/docker/requirements.txt : ${REPO_HOME}/requirements.txt
	@cp ${<} ${@}

BUILD_FILES  = ${REPO_HOME}/build/${ARCH}/docker/Dockerfile
BUILD_FILES += ${REPO_HOME}/build/${ARCH}/docker/entrypoint.sh
BUILD_FILES += ${REPO_HOME}/build/${ARCH}/docker/requirements.txt

BUILD_PATHS  = ${REPO_HOME}/build/${ARCH}/docker

${BUILD_PATHS} :
	@mkdir --parents ${@}

${CLEAN_PATHS} :
	@rm --force --recursive ${@}

# =============================================================================

build : ${BUILD_PATHS} ${BUILD_FILES}
	@docker build $(foreach TAG,${DOCKER_TAGS},--tag ${DOCKER_IMAGE}:${TAG}) --build-arg DATE="$(shell date -u +'%d/%m/%Y-%H:%M:%SZ')" ${REPO_HOME}/build/${ARCH}/docker

clean : ${CLEAN_PATHS}
	@docker images | grep ${DOCKER_IMAGE} | tr --squeeze-repeats ' ' | cut --delimiter=' ' --fields=3 | uniq | xargs --no-run-if-empty docker rmi --force && rm --force --recursive ${BUILD_PATHS}

push  :
	@$(foreach TAG,${DOCKER_TAGS},docker push ${DOCKER_IMAGE}:${TAG} ;)

pull  :
	@$(foreach TAG,${DOCKER_TAGS},docker pull ${DOCKER_IMAGE}:${TAG} ;)

# =============================================================================
