#include "UtilityCommon.h"
#include "../Manager/Generic/SceneManager.h"

int UtilityCommon::Round(float v)
{
    return static_cast<int>(roundf(v));
}

std::vector<std::string> UtilityCommon::Split(std::string& line, char delimiter)
{

    std::istringstream stream(line);
    std::string field;
    std::vector<std::string> result;

    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }

    return result;

}

double UtilityCommon::Rad2DegD(double rad)
{
    return rad * (180.0 / DX_PI);
}

float UtilityCommon::Rad2DegF(float rad)
{
    return rad * (180.0f / DX_PI_F);
}

int UtilityCommon::Rad2DegI(int rad)
{
    return rad * Round(180.0f / DX_PI_F);
}

double UtilityCommon::Deg2RadD(double deg)
{
    return deg * (DX_PI / 180.0);
}

float UtilityCommon::Deg2RadF(float deg)
{
    return deg * (DX_PI_F / 180.0f);
}

int UtilityCommon::Deg2RadI(int deg)
{
    return deg * Round(DX_PI_F / 180.0f);
}

double UtilityCommon::DegIn360(double deg)
{
    deg = fmod(deg, 360.0);
    if (deg < 0.0f)
    {
        deg += 360.0;
    }
    return deg;
}

double UtilityCommon::RadIn2PI(double rad)
{
    rad = fmod(rad, DX_TWO_PI);
    if (rad < 0.0)
    {
        rad += DX_TWO_PI;
    }
    return rad;
}

int UtilityCommon::DirNearAroundRad(float from, float to)
{

    float ret = 1.0f;

    float diff = to - from;

    if (diff >= 0.0f)
    {

        // ��r���������v���Ɉʒu����

        if (diff > DX_PI_F)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA�����v���̕����߂�
            ret = -1.0f;
        }
        else
        {
            // ���v���
            ret = 1.0f;
        }

    }
    else
    {

        // ��r�����������v���Ɉʒu����

        if (diff < -DX_PI_F)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA���v���̕����߂�
            ret = 1.0f;
        }
        else
        {
            // �����v���
            ret = -1.0f;
        }

    }

    return static_cast<int>(ret);

}

int UtilityCommon::DirNearAroundDeg(float from, float to)
{

    float ret = 1.0f;

    float diff = to - from;

    if (diff >= 0.0f)
    {

        // ��r���������v���Ɉʒu����

        if (diff > 180.0f)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA�����v���̕����߂�
            ret = -1.0f;
        }
        else
        {
            // ���v���
            ret = 1.0f;
        }

    }
    else
    {

        // ��r�����������v���Ɉʒu����

        if (diff < -180.0f)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA���v���̕����߂�
            ret = 1.0f;
        }
        else
        {
            // �����v���
            ret = -1.0f;
        }

    }

    return static_cast<int>(ret);

}

int UtilityCommon::Lerp(int start, int end, float t)
{
    // ���`���
    if (t >= 1.0f)
    {
        return end;
    }

    int ret = start;
    ret += Round(t * static_cast<float>(end - start));
    return ret;
}

float UtilityCommon::Lerp(float start, float end, float t)
{
    // ���`���
    if (t >= 1.0f)
    {
        return end;
    }

    float ret = start;
    ret += t * (end - start);
    return ret;
}

double UtilityCommon::Lerp(double start, double end, double t)
{
    // ���`���
    if (t >= 1.0)
    {
        return end;
    }

    double ret = start;
    ret += t * (end - start);
    return ret;
}

Vector2 UtilityCommon::Lerp(const Vector2& start, const Vector2& end, float t)
{
    // ���`���
    if (t >= 1.0f)
    {
        return end;
    }

    Vector2 ret = start;
    ret.x += Round(t * static_cast<float>((end.x - start.x)));
    ret.y += Round(t * static_cast<float>((end.y - start.y)));
    return ret;
}

VECTOR UtilityCommon::Lerp(const VECTOR& start, const VECTOR& end, float t)
{
    // ���`���
    if (t >= 1.0f)
    {
        return end;
    }

    VECTOR ret = start;
    ret.x += t * (end.x - start.x);
    ret.y += t * (end.y - start.y);
    ret.z += t * (end.z - start.z);

    return ret;
}

double UtilityCommon::LerpDeg(double start, double end, double t)
{

    double ret;

    double diff = end - start;
    if (diff < -180.0)
    {
        end += 360.0;
        ret = Lerp(start, end, t);
        if (ret >= 360.0)
        {
            ret -= 360.0;
        }
    }
    else if (diff > 180.0)
    {
        end -= 360.0;
        ret = Lerp(start, end, t);
        if (ret < 0.0)
        {
            ret += 360.0;
        }
    }
    else
    {
        ret = Lerp(start, end, t);
    }

    return ret;

}

COLOR_F UtilityCommon::Lerp(const COLOR_F& start, const COLOR_F& end, float t)
{
    // ���`���
    if (t >= 1.0f)
    {
        return end;
    }

    COLOR_F ret = start;
    ret.r += t * (end.r - start.r);
    ret.g += t * (end.g - start.g);
    ret.b += t * (end.b - start.b);
    ret.a += t * (end.a - start.a);
    return ret;
}

Vector2 UtilityCommon::Bezier(const Vector2& p1, const Vector2& p2, const Vector2& p3, float t)
{
    Vector2 a = Lerp(p1, p2, t);
    Vector2 b = Lerp(p2, p3, t);
    return Lerp(a, b, t);
}

VECTOR UtilityCommon::Bezier(const VECTOR& p1, const VECTOR& p2, const VECTOR& p3, float t)
{
    VECTOR a = Lerp(p1, p2, t);
    VECTOR b = Lerp(p2, p3, t);
    return Lerp(a, b, t);
}

bool UtilityCommon::IsTimeOver(float& totalTime, const float& waitTime)
{
    //�f���^�^�C��
    auto delta = SceneManager::GetInstance().GetDeltaTime();
    totalTime += delta;

    //�ҋ@���Ԃ𒴉߂��Ă��邩���f
    if (totalTime >= waitTime)
    {
        return true;
    }

    return false;
}

int UtilityCommon::WrapIndex(int index, int max)
{
    return (index % max + max) % max;
}

float UtilityCommon::EaseInQuad(const float time, const float start, const float change)
{
    return change * time * time + start;
}

float UtilityCommon::EaseOutQuad(const float time, const float start, const float change)
{
    return -change * time * (time - 2) + start;
}

std::vector<std::vector<int>> UtilityCommon::LoadCSVData(const std::wstring& filePath)
{
    std::vector<std::vector<int>> csvData;

    //�t�@�C���̏���
    std::wifstream ifs = std::wifstream(filePath);
    // ifs.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // UTF-8�Ή�
    if (!ifs)
    {
        OutputDebugString(L"�X�e�[�W��ifstream�������s\n");
        return csvData;
    }

    std::wstring line;

    // CSV�f�[�^�̓ǂݍ���
    while (getline(ifs, line))
    {
        std::wstringstream lineStream(line);
        std::wstring cell;
        std::vector<int> row;

        // �e�Z�����J���}�ŋ�؂��Ď擾���A���l�ɕϊ����čs�ɒǉ�
        while (getline(lineStream, cell, L',')) {
            try
            {
                row.push_back(std::stoi(cell));
            }
            catch (...)
            {
                row.push_back(0); // ���l�ϊ����s����0������
            }
        }
        csvData.push_back(row); // �s��ǉ�
    }

    ifs.close();

    return csvData;
}

std::wstring UtilityCommon::GetWStringFromString(const std::string& str)
{
    //�������𐳂����g���ɂ�2��Ăяo���K�v������
    std::wstring ret = L"";
    //�ŏ��̌Ăяo���͕Ԃ���镶����̕�����
    auto length = MultiByteToWideChar(
        CP_ACP,									//���݂̃R�[�h�y�[�W
        MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,	//�G���[���������Ԃ�
        str.c_str(),							//���̕�����ւ̃|�C���^
        str.length(),							//���̕�����̒���
        nullptr,								//�ϊ���̕�����̃o�b�t�@
        0										//�Ō�̈�����nullptr,0�ɂ��邱�Ƃ�
    );											//wstring�ɕK�v�ȕ����񐔂�Ԃ��Ă���

    if (length <= 0)
    {
        return L"";
    }
    ret.resize(length);	//�K�v�ȃ��������m��

    //���ڂ̌Ăяo���͎��ۂ̕�����𓾂�
    MultiByteToWideChar(
        CP_ACP,									// �����R�[�h
        MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
        str.c_str(),							// �ϊ����̕�����
        str.length(),							// ����ꂽ���C�h�����������A�h���X
        ret.data(),								// ����ꂽ���C�h����������郁�����T�C�Y
        ret.size()								// �ϊ���̕�����̃o�b�t�@�̃T�C�Y
    );

    return ret;
}
