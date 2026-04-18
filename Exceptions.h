//
// Created by Ziv on 24/06/2021.
//

#ifndef EX2PARTB_EXCEPTIONS_H
#define EX2PARTB_EXCEPTIONS_H

#include <iostream>
#include <string>

namespace mtm {

    class Exceptions : std::exception {
    };

    class IllegalArgument : public Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class IllegalCell : public Exceptions {
    public:
        const char *what() const noexcept override;
    };

        class MoveTooFar : public Exceptions {
        public:
            const char *what() const noexcept override;
        };

        class CellOccupied : public Exceptions {
        public:
            const char *what() const noexcept override;
        };

        class OutOfRange : public Exceptions {
        public:
            const char *what() const noexcept override;
        };

        class OutOfAmmo : public Exceptions {
        public:
            const char *what() const noexcept override;
        };


        class CellEmpty : public Exceptions {
        public:
            const char *what() const noexcept override;
        };

        class IllegalTarget : public Exceptions {
        public:
            const char *what() const noexcept override;
        };
    }

#endif //EX2PARTB_EXCEPTIONS_H
