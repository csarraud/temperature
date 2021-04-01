SUMMARY = "Temperature service generator"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = " \
    file://temperature.c \
    file://temperature.service \
"
S = "${WORKDIR}"

inherit systemd

do_compile(){

    # ===== COMPILE TEMPERATURE.C ===== #
    ${CC} ${CFLAGS} ${LDFLAGS} ${S}/${BPN}.c -o ${WORKDIR}/${BPN}
}

do_install(){

    # ===== INSTALL TEMPERATURE SERVICE ===== #
    install -d ${D}${bindir}/
    install -m 0755 ${WORKDIR}/${BPN} ${D}${bindir}
    install -d ${D}${systemd_system_unitdir}/
    install -m 0644 ${WORKDIR}/temperature.service ${D}${systemd_system_unitdir}/
}

SYSTEMD_SERVICE_${PN} = "temperature.service"
SYSTEMD_AUTO_ENABLE = "enable"

FILES_${PN} = " \
    ${bindir}/${BPN} \
    ${systemd_system_unitdir}/temperature.service \
"
