Example 58(=32+26):
# �Z���T�f�o�C�X�p TFTP�N���C�A���g �ݒ�

TFTP�T�[�o�ォ��ݒ�t�@�C�����_�E�����[�h���A���W���[�����̐ݒ��ύX���܂��B  
�{�T���v���ł�ESP-WROOM-02���W���[���̃f�B�[�v�X���[�v���Ԃ�ݒ肷�邱�Ƃ��o���܂��B

## TFTP�Ƃ�

TFTP�̓l�b�g���[�N�@��Ȃǂ̐ݒ�t�@�C����t�@�[���E�F�A��]������Ƃ��Ɏg�p�����f�[�^�]���v���g�R���ł��B  
�g�����肪�ȒP�ŁA�v���g�R�����ȒP�Ȃ̂ŁA�@��̃����e�i���X�Ɍ����Ă��܂��B�ʏ�A�F�؂�Í����Ƃ��������Ƃ͍s�킸�A�]�����̂ݗL���ɂ���A�������͕ύX����Ă����̖����p�r�ŗ��p���܂��B

## �{�T���v���̎d�l

TFTP�ŁuADC_PIN=�s���ԍ��v�𑗐M����ƁAESP���W���[����ADC���̓s����ύX���邱�Ƃ��o���܂��B�܂��A�uSLEEP_SEC=���ԁi�b�j�v�𑗐M����ƁAESP���W���[���̃X���[�v�Ԋu��ύX���邱�Ƃ��o���܂��B

## Raspberry Pi�ւ�TFTP�T�[�o�̃C���X�g�[�����@

    $ sudo apt-get install tftpd-hpa
    
## �ݒ�t�@�C��(/etc/default/tftpd-hpa) �̗�

    # /etc/default/tftpd-hpa
    TFTP_USERNAME="tftp"
    TFTP_DIRECTORY="/srv/tftp"
    TFTP_ADDRESS="0.0.0.0:69"

## TFTP�T�[�o�̋N���ƒ�~

    $ chmod 755 /srv/tftp
    $ sudo /etc/init.d/tftpd-hpa start
    $ sudo /etc/init.d/tftpd-hpa stop

## �]���p�̃t�@�C����ۑ�

    $ echo "; Hello! This is from RasPi" > /srv/tftp/tftpc_1.ini
    $ echo "ADC_PIN=32" >> /srv/tftp/tftpc_1.ini
    $ echo "SLEEP_SEC=50" >> /srv/tftp/tftpc_1.ini
    $ chmod 644 /srv/tftp/tftpc_1.ini
    $ cat /srv/tftp/tftpc_1.ini
    ; Hello! This is from RasPi
    ADC_PIN=32
    SLEEP_SEC=50

## ���ӎ���

* TFTP�N���C�A���g(ESP��)��TFTP�T�[�o(PC��Raspberry Pi��)�N������ƁA�e�@�킪�Z�L�����e�B�̋��Ђɂ��炳�ꂽ��ԂƂȂ�܂��B
* �܂��A�E�B���X�⃏�[�����N������ƁA�����l�b�g���[�N��̑S�Ă̋@��֊������鋰�ꂪ���܂�܂��B
* �C���^�[�l�b�g�ɐڑ�����ƊO������̐N�������ꍇ������܂��B
* TFTP�N���C�A���g�͏��Ȃ��Ƃ����[�J���l�b�g���݂̂œ��삳����悤�ɂ��ĉ������B
* TFTP���s�K�v�ȂƂ��́A��~�����Ă��������B

Copyright (c) 2016-2018 Wataru KUNINO
https://bokunimo.net/
