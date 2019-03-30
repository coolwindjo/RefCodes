// Observer.h
//#pragma once    // C11���� ���� ǥ������ ä�õǾ����ϴ�. - g++������ ������
#ifndef IOBSERVER_H
#define IOBSERVER_H

struct IObserver
{
    virtual void on_update(void* data) = 0;
    virtual ~IObserver() {}
};

#endif // !IOBSERVER_H