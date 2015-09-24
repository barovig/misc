using namespace std;

// this small class represents a point in 2D plane(was a struct but need to overload operator. inelegant, should rewrite controls handling in main()
class p {
public:
	int x;
	int y;
	bool operator!=(const p& other);
};



// properties:
enum Prop : int {EMPTY = 0, BORDER, TAP, BAR, RZAG, LZAG, CUBE, RHOOK, LHOOK}; 

class CFigure
{
public:
	CFigure(void);
	~CFigure(void);
	void Rotate(void);
	void MoveDown(void);
	void SetPivot(int px, int py);
	void SetPointList(vector<p> pList);
	vector<p> GetPointList(void);
	void MoveLeft(void);
	void MoveRight(void);

private:
	vector<p> m_ptList;		//contains list of points that create a figure
	p m_Pivot;				// pivot point of rotation of the figure
	Prop m_Prop;
	int m_RotState;
	//add private methods to rotate each figure (m_Prop) type
	void RotateTap(void);
public:
	Prop GetProperty(void);
	void SetProperty(Prop prop);

private:
	void RotateLZag(void);
	void RotateRZag(void);
	void RotateBar(void);
	void RotateLHook(void);
	void RotateRHook(void);
};

