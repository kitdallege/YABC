#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
    public:
        System();
        virtual ~System();

        virtual void update(float delta) = 0;

    protected:

    private:
};

#endif // SYSTEM_H
