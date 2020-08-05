#include "stateMachine.hpp"

namespace bfb {
template <class Concrete, typename ValidStates, std::uint32_t priority>
Logger StateMachine<Concrete, ValidStates, priority>::stateMachineLog{};
}