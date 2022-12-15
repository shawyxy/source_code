#pragma once
namespace xy
{
	template<size_t N>		// N������λ	
	class bitset
	{
	public:
		bitset()
		{
			_bits.resize(N / 8 + 1, 0);
		}
		void set(size_t pos)
		{
			assert(pos < N);

			size_t x = pos / 8;			// ��x��char
			size_t y = pos % 8;			// �����char�ĵ�y������λ
			_bits[x] |= (1 << y);		// ���������λ��Ϊ1
		}
		void reset(size_t pos)
		{
			assert(pos < N);

			size_t x = pos / 8;			// ��x��char
			size_t y = pos % 8;			// �����char�ĵ�y������λ
			_bits[x] &= (~(1 << y));	// ���������λ��Ϊ0
		}
		void flip(size_t pos)
		{
			assert(pos < N);

			size_t x = pos / 8;			// ��x��char
			size_t y = pos % 8;			// �����char�ĵ�y������λ
			_bits[x] ^= (1 << y);		// ���������λȡ��
		}
		void test(size_t pos)
		{
			assert(pos < N);

			size_t x = pos / 8;			// ��x��char
			size_t y = pos % 8;			// �����char�ĵ�y������λ
			if (_bits[x] & (1 << y))	// ��λ�ѱ�����
				return true;
			else
				return false;
		}
		size_t size()
		{
			return N;
		}
		size_t count()
		{
			size_t count = 0;
			for (auto e : _bits)
			{
				char num = e;
				while (num)
				{
					num &= num - 1;
					count++;
				}
			}
			return count;
		}
		bool any()
		{
			for (auto e : _bits)
			{
				if (e != (char)0)
					return true;
			}
			return false;
		}
		bool none()
		{
			return !any();
		}
		bool all()
		{
			size_t size = _bits.size();
			for (size_t i = 0; i < size - 1; i++)	// ǰsize-1��������char
			{
				if (_bits[i] != (char)127)
					return false;
			}
			for (size_t i = 0; i < N % 8; i++)		// ���һ��char��ʣ��λ
			{
				if ((_bits[size - 1] & (1 << i)) == (char)0)
					return false;
			}
			return true;
		}
		void Print()
		{
			string ret = "";
			size_t size = _bits.size();
			for (size_t i = 0; i < size - 1; i++)
			{
				for (size_t j = 0; j < 8; j++)
				{
					if (_bits[i] & (1 << j))
						ret += "1";
					else
						ret += "0";
				}
			}
			for (size_t j = 0; j < N % 8; j++)
			{
				if (_bits[size - 1] & (1 << j))
					ret += "1";
				else
					ret += "0";
			}

			cout << ret << endl;
		}
	private:
		vector<char> _bits; // ��charΪ��λ����
	};
}

