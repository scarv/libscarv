# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

FROM ubuntu

ARG BRANCH
ARG DATE

LABEL maintainer="SCARV project <info@scarv.org>" url="https://github.com/scarv/libscarv" branch="${BRANCH}" date="${DATE}" 

# -----------------------------------------------------------------------------

COPY ./requirements.txt /tmp/requirements.txt

RUN apt-get --assume-yes --quiet update \
 && apt-get --assume-yes --quiet install apt-utils gettext-base gosu sudo python3 python3-pip python3-venv \
 && pip3                         install -r /tmp/requirements.txt

# -----------------------------------------------------------------------------

include(`Dockerfile.in')

# -----------------------------------------------------------------------------

COPY ./entrypoint.sh /usr/sbin/entrypoint.sh
RUN chmod 755 /usr/sbin/entrypoint.sh
ENTRYPOINT [ "/usr/sbin/entrypoint.sh" ]

# =============================================================================
