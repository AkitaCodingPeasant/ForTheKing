# For the King

## �����W�d

### Coding Style

- ���i�ϥΨ㦳�~���s���� Global Variable�F�Y�n�ϥ� Global Variable�A�h�ݭn�T�O��L�H�u��̾a�B�~�� Function �Ӧs�� Global Variable �� Data
- Class ���� Data ���i�Q�~���ާ@�����s���A�ݭn�إ߱M���� Getter �P Setter
- Function ��Ƥ��y�W�L 150 ��
- Function �ǤJ�� Variable ����W�L 7 �ӡA�åB Function ��������ϥ�**�D Const**�� Global Variable
- Function ���Y�i���Ƥ����W�L 4�A�_�h�ݭn�B�~�ϥα������� Helper
- �C�� Source File �u��ޥΨ�ۦP�W�٪� Header File
- �Y�禡�㦳 inline�A�h���ө�b�ɮ׫�� .inl ���P�W�ɮפ��A�@����������{
- �C�� Header File ���ݭn������
- �R�W����Τ@���m�p���R�W�k

### Commit Style

Commit �������ӥH�U���榡�i��

```
{HEADER} - �K�n���� Commit �����e
(OPTION) <Body> - �Բӻ����o�������e
(OPTION) <Footer> - �B�~���O
```

Header �@���K�O���n�L���FBody �i�H�y�z�o�����檺�ԲӤ��e�FFooter �i�H�����B�~���O�ϥ�

- - Headers
    - FEAT : �s���\��
    - FIX : �״_���~
    - DOCS : Document �������ק� (CHANGELOG�BREADME�B...)
    - PERF : �į�ﵽ�A�άO�W�[�l�ܮį઺ Code
    - TEST : �s�W���դ��
    - STYLE : ��­ק�{���X�������[�ƪ�
    - DEPRECATE : �^�O�Y�Ǥ����n�� Feature �άO�\��
    - REFACTOR : ���K�[�s�\��άO�״_ Bug �����p�U���c�{���[�c (���p���ҲաB��n���g�k�B...)
    - RELEASE : �M�������������O
    - CI : ��� CI �����]�w���վ�

Ref : https://isoneet.org/web-learning/devTools/git.html#commit-message

### Development Criterion

�b�}�o�s�\��ɥ����s�W Branch�A�åB�ݥ��M Main Branch ���� Merge�A�åB�b Merge ��S���X�{ Bug �ɤ~��o�e Pull Request �M Main Branch �� Merge

Branch �������ӥH�U�R�W�W�d

```
{NAME}-{STATUS}
```

- Name
    - Name �i�H�񥿦b�i��}�o�� class �άO Feature ���W��
- Status
    - DEV : �}�o�s�\��
    - FIX : �״_�{�� Bug
    - REBUILD : ���c�{���[�c

�p�G���|�ϥ� Branch �H�U�����ѩR�O

```
// �إ� Branch
git checkout -b className-DEV

// ���� Branch
git checkout branchName

// �T�{�ثe�Ҧb Branch

git status
git checkout
```