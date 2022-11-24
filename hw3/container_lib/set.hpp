#pragma once

template<class T>
hw3::Set<T>::Set([[maybe_unused]] std::initializer_list<T> init) {
    std::ranges::for_each(init, [](const auto &el) { std::cout << el << ' '; });
    std::cout << '\n';
    return ;
}
