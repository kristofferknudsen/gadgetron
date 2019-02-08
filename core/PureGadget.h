#pragma once
#include "Node.h"

namespace Gadgetron::Core {
class PureGadget : public GadgetNode {
public:
    using GadgetNode::GadgetNode;

    void process(InputChannel& in, OutputChannel& out) final
    {
        for (auto message : in )
            out.push(this->process_function(std::move(message)));
    }

    virtual Message process_function(Message) const = 0;
};

template <class RETURN, class ARG>
class TypedPureGadget : public PureGadget {
public:
    using PureGadget::PureGadget;
    Message process_function(Message message) const override{
        if (!convertible_to<ARG>(message)) return message;
        return  Message(process_function(force_unpack<ARG>(std::move(message))));
    }
    virtual RETURN process_function(ARG args) const = 0;

};
}
