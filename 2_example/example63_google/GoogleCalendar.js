/*******************************************************************************
Google �J�����_�[(�\��\) ����\����擾����

                                                Copyright (c) 2018 Wataru KUNINO
********************************************************************************
���s���@
    1. Google Apps Script(https://script.google.com/)�փA�N�Z�X
    2. �{�X�N���v�g���y�[�X�g���A��ʓ����j���[��[�t�@�C��]��[�ۑ�]�����s
    3. [�v���W�F�N�g���̕ҏW]��ʂŃv���W�F�N�g������͂��āA[OK]���N���b�N
    4. [���J]���j���[����[�E�F�u�A�v���P�[�V�����Ƃ��ē���]��I��
    5. [���F���K�v�ł�]�̃��b�Z�[�W���\�������̂�[�����m�F]���N���b�N
    6. [�A�J�E���g�I��]��ʂŎ����̃A�J�E���g��I�����A[����]���N���b�N
    7. ����[���̃��[�U�Ƃ��ăA�v���P�[�V���������s]�Ŏ����̃A�J�E���g��I��
    8. ����[�A�v���P�[�V�����ɃA�N�Z�X�ł��郆�[�U�[]��[�S��]��I��
    9. [����]�������ƌ��JURL���\�������̂ŁA�R�s�[����
    10. �R�s�[�������JURL���u���E�U�ŃA�N�Z�X���A����m�F

�o�͌`��
    Length,�\�萔
    ��,��,�^�C�g��1
    ��,��,�^�C�g��2
    ...(6���Ԉȓ��̑S�\��)...
    [EOF]

�Q�l�����F
    https://github.com/bokunimowakaru/esp/tree/master/2_example/example63_google
    https://github.com/wilda17/ESP8266-Google-Calendar-Arduino
    https://developers.google.com/apps-script/reference/calendar/calendar-app
*******************************************************************************/

function doGet(){
  return ContentService.createTextOutput(GetEvents());
}

function GetEvents(){
  var Now = new Date();
  var EndTime = new Date(Now.getTime() + (6 * 60 * 60 * 1000));
  Logger.log("Start " + Now);
  Logger.log("End " + EndTime);
  var events = CalendarApp.getEvents(Now, EndTime);
  Logger.log(events.length + " Events");
  str = "Length," + events.length + '\n';
  for (var i = 0; i < events.length; i++){
    str += events[i].getStartTime().getHours() + ',';
    str += events[i].getStartTime().getMinutes() + ',';
    str += events[i].getTitle();
    str += '\n';
  }
  str += "[EOF]";
  Logger.log("retrun str\n" + str);
  return str;
}
