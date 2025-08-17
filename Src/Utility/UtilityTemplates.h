#pragma once
#include <vector>
#include <algorithm>

// �e���v���[�g��p���[�e�B���e�B�N���X
class UtilityTemplates
{
public:

    /// <summary>
    /// �z����ɒl�����邩���ׂ�
    /// </summary>
    /// <typeparam name="T">�z����̗v�f�̌^</typeparam>
    /// <param name="vec">�����Ώۂ̔z��</param>
    /// <param name="value">��������l</param>
    /// <returns>�l���������true,�Ȃ����false��Ԃ�</returns>
    template<typename T>
    static bool ContainsValue(const std::vector<T>& vec, const T& value) 
    {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }
};