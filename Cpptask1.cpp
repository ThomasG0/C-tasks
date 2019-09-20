// C++14
class ComplexNumber 
{
		int Re;
		int Im;
	public:
		constexpr ComplexNumber(const int setRe = 0, const int setIm = 0): 
			Re(setRe),
			Im(setIm) 
		{}
		constexpr void SetRe(const int newRe)
		{
			this->Re = newRe;
		}
		constexpr void SetIm(const int newIm)
		{
			this->Im = newIm;
		}
		constexpr int GetRe() const
		{
			return this->Re;
		}
		constexpr int GetIm() const
		{
			return this->Im;
		}
		constexpr bool operator == (const ComplexNumber other) const
		{
			return (other.GetRe() == this->Re) && (other.GetIm() == this->Im);
		}
};

constexpr ComplexNumber Conjugate(const ComplexNumber& x)
{
	ComplexNumber res;
	res.SetRe(x.GetRe());
	res.SetIm(-x.GetIm());
	return res;
}

int main()
{
	constexpr ComplexNumber a(1, 2);
	constexpr ComplexNumber b(1, -2);
	constexpr auto c = Conjugate(a);
	static_assert(b == c, "failed");
}
