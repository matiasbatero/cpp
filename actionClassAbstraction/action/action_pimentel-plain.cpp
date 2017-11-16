#include <iostream>

class Action
{
	public:

	virtual void Execute(void)=0;

};

class Context
{
    public:
        void update(){std::cout << "context update" << std::endl;}
};

class UpdateAction : public Action
{
	private:
        Context* c;
        virtual void Execute() { c->update(); };
	public:
        UpdateAction(Context* context) : c(context){ Execute(); };
};

int main()
{
    Context* context = new Context;
    UpdateAction* action = new UpdateAction(context);
}
