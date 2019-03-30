// Observer.h
//#pragma once    // C11에서 공식 표준으로 채택되었습니다. - g++에서도 지원함
#ifndef IOBSERVER_H
#define IOBSERVER_H

struct IObserver
{
    virtual void on_update(void* data) = 0;
    virtual ~IObserver() {}
};

#endif // !IOBSERVER_H